#include <iostream>
#include <pbc/pbc.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888

void generate_trapdoor() {
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
    element_t K1, K2, Tw;
    element_init_G1(K1, pairing);
    element_init_G1(K2, pairing);
    element_init_G1(Tw, pairing);

    // Assume IDS, IDR, PIDS, PIDR, and w are initialized
    element_t IDS, IDR, PIDS, PIDR, w;
    // Initialize IDS, IDR, PIDS, PIDR, w elements

    // Compute K1 = e(H(IDS), DIR)
    element_t H_IDS, DIR;
    element_init_G1(H_IDS, pairing);
    element_init_G1(DIR, pairing);
    // Compute H(IDS) and DIR based on IDs

    element_pairing(K1, H_IDS, DIR);

    // Compute K2 = xIDR * PIDS
    element_t xIDR_PIDS;
    element_init_G1(xIDR_PIDS, pairing);
    element_mul(xIDR_PIDS, xIDR, PIDS);

    // Compute Tw = h1(IDS, PIDS, IDR, PIDR, K1, K2, w)
    element_t h1_result;
    element_init_Zr(h1_result, pairing);
    // Compute h1(IDS, PIDS, IDR, PIDR, K1, K2, w) based on hash functions

    // Serialize Tw into a string
    char* Tw_str = nullptr;
    size_t Tw_str_len = element_length_in_bytes(Tw);
    Tw_str = (char*) malloc(Tw_str_len);
    element_to_bytes((unsigned char*) Tw_str, Tw);

    // Send Tw_str to the server
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

    send(sock, Tw_str, Tw_str_len, 0);

    // Clean up
    free(Tw_str);
    element_clear(K1);
    element_clear(K2);
    element_clear(Tw);
    element_clear(H_IDS);
    element_clear(DIR);
    element_clear(xIDR_PIDS);
    element_clear(h1_result);
    pairing_clear(pairing);
    close(sock);
}

int main() {
    generate_trapdoor();
    return 0;
}
