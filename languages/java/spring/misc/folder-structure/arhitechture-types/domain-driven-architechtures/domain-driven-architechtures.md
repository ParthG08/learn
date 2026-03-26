# Architechture

Here in the loankhata folder in the project directory there are different packages

Main.java           
creditscore             
crons                   
datalake                
dbcleanup               
eligibilityreport       
featurestore            
foreclosure             
health                  
hibernate               
insightdataservice      


These folders under com.khatabook.loankhata are Java packages. They represent the modular structure of the loans-service application.

This repository follows a **Domain-Driven Design** (DDD) or a highly feature-oriented architecture. Instead of organizing by technical layer 

(e.g., having one big controllers folder and one big services folder for the whole app), the code is split into **functional domains**.

Each folder represents a specific business capability or a sub-module of the loan system. For example:

**loan**/: Likely contains core loan management (creation, retrieval, basic loan logic).

**repayments**/: Handles repayment logic, schedules, and processing.

**auth**/: Manages authentication and user identity for the service.

**common**/: Contains shared infrastructure, utilities, and configurations (e.g., networking, database config, global constants) used by all other modules.

**loans**/ (Loan Origination System): Handles the process from application to loan disbursal.

**creditscore**/: Manages integration with credit bureaus and scoring logic.

**notifications**/: Handles sending SMS, email, or push notifications to users.

Why is it structured this way?

Separation of Concerns: Each folder (module) is responsible for a specific part of the business. Changes in repayments are less likely to accidentally break the creditscore logic.

**Scalability**: New features can be added by creating a new folder without cluttering existing ones.

**Encapsulation**: Each module typically has its own controller/, service/, repository/, and models/ internally (as seen in the loan/ and repayments/ folders), keeping related code together.

**Reusability**: Shared code is strictly kept in common/, making it easy to see what is generic 
versus what is feature-specific.

In short, these are the building blocks of the Loans Service, where each block focuses on one specific aspect of the loan lifecycle or system requirement.





