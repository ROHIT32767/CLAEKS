#include <iostream>
#include <pbc/pbc.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888

void clkaes_encryption(const char* ID_S, const char* ID_R, const char* w) {
    // Initialize pairing parameters
    pairing_t pairing;
    pairing_init_set_str(pairing, "type a\np 1073676287\n\
    671186175 1998892341 1719141053 56749017 152657920 851228295 135189515\
    860193030 318417786 153785537\nr 1155099583\nh 645963713\
    606269457 306760787 172022522 89890330 335395041 73834659 211813417\
    454252155 448663646 287955863 789060746 318281590 72509247 1104867993\
    395179634 646825477 128630025 1081554404 487165188 493354931 299887315\
    1035893415 31301333 740313184 632855107 778238856 334634782 316613177\
    706703833 325179047 897125513 405133695 1180637845 895234512 105289287\
    251974321 1018081954 588615485 414702568 479107963 744836889 100441284\
    933459268 652465846 450305826 511631958 121516586 822778994 684122464\
    658123526 5704412 657831189 422587139 715377355 35294080 425020065\
    110180744 311768168 719117401 737724107 1047393305 399261352 634748821\
    646038272 481810268 263346372 1133922306 103962282 709289672 186301409\
    507547295 1080539654 740650282 417271481 1070276893 348440107 668840502\
    255541988 707550528 1083189299 1035118507 737671430 146646370 361605907\
    365212485 392110251 545948712 466825775 1093780167 137707278 280855728\
    558469168 318713372 444126591 123839206 1276125291 996046927 431386946\
    147127366 352515527 580548690 303409913 929515302 116871759 756950424\
    938067900 391603145 1170084689 38699948 806443425 1075249532 207416710\
    128951893 210163147 312801593 661033174 898038715 1199484227 29137051\
    125867616 492324979 1165933690 914715331 570727366 589064515 1093076821\
    138930918 545107352 829055832 229782756 1225419126 1074025460 773431684\
    386788564 1203113623 484394563 1020488347 93818985 180374686 267903938\
    22458820 547332028 1027150666 257931381 1060706611 42325907 587660585\
    318975851 80170560 987750303 133158859 582067979 260743583 927937991\
    1041347411 229150284 676395081 924758108 829414918 927160387 687890681\
    626250839 352594832 205049480 137061043 982870402 122314153 429028257\n\
    q 134661323\n\
    1096095484 686005835 1096095484 509450932 369040760 952876725 1182658752\
    687889765 1024296021 95998696");

    // Generate elements
    element_t K1, K2, C1, C2, P_ID_S, P_ID_R;
    element_init_GT(K1, pairing);
    element_init_G1(K2, pairing);
    element_init_G1(C1, pairing);
    element_init_G1(C2, pairing);
    element_init_G1(P_ID_S, pairing);
    element_init_G1(P_ID_R, pairing);

    // Assume P_ID_S and P_ID_R are initialized based on public keys of ID_S and ID_R

    // Choose a random number r in Z*q
    element_t r;
    element_init_Zr(r, pairing);
    element_random(r);

    // Compute K1 = e(D_ID_S, H(ID_R)) where D_ID_S is the partial private key of ID_S
    element_t D_ID_S, H_ID_R;
    element_init_G1(D_ID_S, pairing);
    element_init_G1(H_ID_R, pairing);
    // Compute D_ID_S and H(ID_R) based on ID_S and ID_R

    element_pairing(K1, D_ID_S, H_ID_R);

    // Compute K2 = x_ID_S * P_ID_R where x_ID_S is the secret value of ID_S
    element_t x_ID_S_P_ID_R;
    element_init_G1(x_ID_S_P_ID_R, pairing);
    // Compute x_ID_S * P_ID_R based on x_ID_S and P_ID_R

    element_mul(x_ID_S_P_ID_R, x_ID_S, P_ID_R);

    // Compute C1 = r * P_ID_S
    element_mul(C1, P_ID_S, r);

    // Compute C2 = r * h2(h1(ID_S, P_ID_S, ID_R, P_ID_R, K1, K2, w)) * P
    element_t h1_result, h2_result, h1_input, h2_input;
    element_init_Zr(h1_result, pairing);
    element_init_G1(h2_result, pairing);
    element_init_GT(h1_input, pairing);
    element_init_G1(h2_input, pairing);
    // Compute h1(ID_S, P_ID_S, ID_R, P_ID_R, K1, K2, w) based on hash functions
    // Compute h2(h1_result) based on hash functions

    element_mul(C2, h2_result, C1);

    // Serialize C1 and C2 into strings
    char* C1_str = nullptr;
    char* C2_str = nullptr;
    size_t C1_str_len = element_length_in_bytes(C1);
    size_t C2_str_len = element_length_in_bytes(C2);
    C1_str = (char*) malloc(C1_str_len);
    C2_str = (char*) malloc(C2_str_len);
    element_to_bytes((unsigned char*) C1_str, C1);
    element_to_bytes((unsigned char*) C2_str, C2);

    // Send C1_str and C2_str to the server
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Socket creation failed...\n";
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) != 0) {
        std::cerr << "Connection with the server failed...\n";
        exit(EXIT_FAILURE);
    }

    send(sock, C1_str, C1_str_len, 0);
    send(sock, C2_str, C2_str_len, 0);

    // Clean up
    free(C1_str);
    free(C2_str);
    element_clear(K1);
    element_clear(K2);
    element_clear(C1);
    element_clear(C2);
    element_clear(P_ID_S);
    element_clear(P_ID_R);
    element_clear(r);
    element_clear(D_ID_S);
    element_clear(H_ID_R);
    element_clear(x_ID_S_P_ID_R);
    element_clear(h1_result);
    element_clear(h2_result);
    element_clear(h1_input);
    element_clear(h2_input);
    pairing_clear(pairing);
    close(sock);
}

int main() {
    const char* ID_S = "sender_id";
    const char* ID_R = "receiver_id";
    const char* keyword = "search_keyword";

    clkaes_encryption(ID_S, ID_R, keyword);

    return 0;
}
