# HRS Workflow File structure - Actions
Lets understand the structure of a HRS Workflow file

Although it has many attributes , there are 2 main important attributes in its structure

Lets start with the "actions" attribute

"actions" attribute is a list of actions , where each action contains a name , instanceName along with input and output attributes. Each input has a name and value

# HRS Workflow File structure - Links

Another important attribute is the "links" attribute

"links" attribute is a list of links , where each link contains reference to its source and target action and the condition under which the link is executed.

While analysing the structure of a HRS Workflow file , we found out that most of the attributes are boilerplate code that dont actually contribute to the execution of the workflow. There are also attributes that can be modelled from "actions" and "links" attributes.

# Experiments

We started with experimenting to create a HRS Workflow file from resolution steps


# Detailed Demo
Snehil , could you please share your screen once again

We have used Gemini 1.5 pro for the demonstration

We start with the User input , the user input contains steps to resolve an autosys alert by checking the status of the autosys job and notifying the user accordingly.

We perform few shot prompting on the user input and generate the resolution steps.

Snehil could you please run the prompt

We use Approach II to convert the resolution steps to the Alternative representation 

Lets understand the prompt now

We start with giving an overview of actions , links , inputs and outputs in HRS workflow.
Then we continue by providing the Action summary of Top 60 actions
Each Action in the Action summary consists of its description and the summary of input and output attributes.

We then provide the list of all global variables as context.

Now , we provide the resolution steps obtained from the user input in the previous step.

Then , we provide the Output format of the prompt which is the structure of the Alternative representation we proposed earlier.

In the Output summary , we explain the LLM as to how exactly it has to structure the Output format given the resolution steps.

For example , 

...READ THE GLOBAL TYPE DESCRIPTION...

Now this prompt is given to the LLM and it outputs the Alternative representation.

Snehil could you please run the second prompt

We then convert the Alternative Representation to a HRS Workflow file using a python script.

Snehil , could you please generate the HRS Workflow file using the python script

Now , lets upload the generated file to HRS Studio and view the output

As we can see, the HRS Workflow is similar to the expected output workflow.

# HRS Complexities
Now that we have seen a detailed demo , lets discuss regarding the complexities in a HRS Workflow

# CONSTANT
Firstly we experimented on using CONSTANT variable types in the workflow.

A CONSTANT variable is when a user assigns a value to a variable and that value remains constant throughout the workflow.

We explain in the output summary of the prompt that it has to assign a variable the type "CONSTANT" if the value assigned is a constant.

For example, In the given workflow the Timer action has an input attribute called "minutes" which is set to the value 5. If we look at step 4 in the resolution steps,

"Upon success in step 2 , snooze the workflow for a specific duration given time in minutes. Inputs = [minutes="10"]"

From the resolution steps , the LLM identifies that the value 10 is a constant value and hence it is marked as a CONSTANT variable.

# GLOBAL
Next we moved onto handling GLOBAL variable types in the workflow.

Global variables contain information related to specific properties of an alert. There are fixed number of global variables in the HRS system. 
In this example, Context_Data_AlertGroup can be used to find the jobName of the Autosys alert.

In the prompt , as we have explained earlier , we provide the list of all global variables as context.

We explain in the output summary of the prompt that the LLM has to assign a variable the type "GLOBAL" by checking whether if the value of a variable is part of the provided list of global variables or not

For example, If we look at step 2 in the resolution steps,

"Upon success in step 1, Set workflow global variables given variable name and value respectively. Outputs = [jobName = "ContextData_AlertGroup" , instance="ContextData_ClassSource"]

From the resolution steps , the LLM identifies that the value "ContextData_AlertGroup" is part of the global variables list and hence it is marked as a GLOBAL variable.

# ACTION
Further we experimented on handling ACTION variable types in the workflow.

An ACTION variable is when a user assigns a value to a variable and that value is derived from the output of another action in the workflow.

We explain in the output summary that the LLM has to assign a variable the type "ACTION" if the values are derived from another resolution step

For example , if we look at step 5 in the resolution steps,

Upon success in step 4, retrieve the status of an Autosys Job. Here jobName input value is same as jobName output defined in step 2 and autosysInstance input value is same as instance output defined in step 2.

From the resolution steps , the LLM identifies that the value of jobName and autosysInstance are derived from the output of step 2 and hence it is marked as an ACTION variable. Here we also store the instanceName of the action the variable is derived from in the Alterntative representation.

# Multiple Branches

Finally we experimented on handling multiple branches in the workflow.

In the prompt we provide an additional condition apart from success and failure conditions. 

We explain in the output summary that the LLM has to store variables in the "additionalExpression" attribute of a link if there is an additional condition apart from success and failure conditions.

For example, if we look at step 7 and step 8 of the resolution steps ,

Upon success in step 5 and if status=="RUNNING" , close the alert

Upon success in step 5 and if status=="FAILURE" , execute the command on the host given hostname , systemaccount.....

From the resolution steps, the LLM identifies that there are additional conditions apart from success and failure conditions and hence stores the output variable name and the conditional value associated with it in the "additionalExpression" attribute of the link.

# Comparision slide

Now that we have seen the complexities in the HRS workflow , lets compare the results of the LLM model with the actual workflow

# Comparision - length

We also experimented on constructing a larger workflow and as you can see the output workflows are similar. While handling larger workflows , we observed that there might be actions that are repeated in the workflow , in such cases we identify a particular action by its instanceName which is the name of the action appended by the number of occurence.

# From Automation Runbook to HRS Workflow
What did not work
LLM did not properly output some attributes in the .wfs file and couldnt properly format escape characters in the .wfs file.
Although it looked as if the LLM output the correct stucture , it often used to miss out on some attributes in the .wfs file.

# Conclusions
Most importantly this project serves as a Proof of Concept for the automation of creating HRS workflows from Automation Runbooks. 

# Future Work


# Learnings
Networking: Built a robust network through events and continuous engagement with peers.
Teamwork and Collaboration: Strengthened teamwork skills through regular catch-ups and inclusive practices.
Learning from Experience of Other People: Gained valuable insights from the journeys and hobbies of team members and other employees.
Problem Solving Approach: Enhanced my problem-solving skills by addressing errors with POSTMAN and git repositories.
Application of Deep Learning Concepts in Real Projects: Applied deep learning concepts effectively in real-world projects.


# Acknowledgements







