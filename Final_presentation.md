# Intro Slide
Hello Everyone , I am Rohit , and am an intern in the PRX/ML team. 
Today I will be presenting my work on HRS Copilot that I have done over the past 2 months as part of my Summer Internship Project

# HRS
So to start with , What is HRS ?
HRS is Health Restoration Service
HRS is an automation framework to automate operational toil in production

Alerts are generated in our system and operation teams resolve these alerts , but as alert volume increases , it implies that the operation team size should increase.

To mitigate these repetitive alerts , we configure workflows and once the the steps in the workflow are followed , we close the alert

In the current scenario , when an alert is detected an ASM ticket is raised by the Appbank that is forwarded to the SPARC team that generates an Automation Runbook to close the alert. Once the Automation Runbook is generated , the Operation team translates the logical resolution steps that are part of the runbook into a HRS workflow , Once the workflow is created it is tested by the AppBank Team and is then deployed.

Whenever the same alert is raised again , instead of manually closing it again , the deployed workflow gets invoked by the FABRIC policy and the alert is automatically closed

## Demo of HRS Studio
It provides a complete automation stack for development engineers to diagnose and resolve a production situation to reduce the mean time to repair.

HRS basically provides us with a set of runtime controls and UI known as the Workflow studio where we can drag and drop components to construct a workflow and deploy them.

It also provides an embedded test environment to validate workflows before hitting the production environment. It basically follows a low-code approach to reduce users learning curve and improve their development experience

# HRS Workflow types
We have 6 main workflow types in HRS studio

Resolution - These type of workflows are triggered using FABRIC policy and are mainly used for alert resolution use case

Monitoring - These types of workflows are used where we want to close the alert when it reaches a particular state

Enrichment - These type of workflows are used where HRS adds some more details for the operation team to close the alert

Validation - These type of workflows can be used to check whether if an alert is closed correctly , if its not closed correctly it generates a new alert

OnDemand - These type of workflows can be triggered manually 

Reovery - These workflows are used for disaster recovery events

Based on an Analysis that we have performed , we have found out that 70% of the existing workflows on HRS are of the resolution type , Hence we have focused on resolution workflows in our project

# Problem Statement
The focus of the project was to generate .wfs file given logical description of alert resolution steps

In short , we aim to democratize the process of creating HRS workflows

The Project Objectives include finding conclusive answers to each of the objectives mentioned through experiments

....Read Project Objectives....

# Large Language Models - LLM
Lets discuss about LLMs , LLMs are Large Language Models

A language model is a probabilistic model that assigns probabilities to sequence of words. We usually train a neural network to predict these probabilites.

Large Language Model is a neural network trained on a large corpora of text. The underlying transformer is a set of neural networks that consist of an encoder and a decoder with self-attention capabilities. Self attention is basically allowing the model to weigh the importance of different words in a sequence relative to each other. The encoder and decoder extract meanings from a sequence of text and understand the relationships between words and phrases in it.

# Large Language Models - LLM
As we have discussed , LLMs are specialised in next word prediction , through this functionality they can basically perform a wide range of capabilities like ...read them out...

There are many open source language models like ...read out the slide...

# Tokenisation



