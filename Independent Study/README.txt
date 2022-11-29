//Independent Study Summer 2021
//Project 2
//IGLI DURO



// ============ How to start the application =================

//You must have NodeJS and NPM installed.

// https://nodejs.org/en/download/


//Afterwards install dependencies for the server and client with  

npm install

//and 

npm client-install


//To run the application locally run the command below inside the terminal while in the root directory. This will run both the client and server at the same time.

npm run dev 

//To deploy the application online using Heroku you must have Git and Heroku installed. If you don't, follow this install and setup guide, https://devcenter.heroku.com/articles/getting-started-with-nodejs



// ==============================================================  




// ===================== Configurations =========================


// =========  MongoDB Atlas ========

//In config/keys.js and config/db.js replace "MONGODB_CONNECTION_STRING" with your own connection string.

//1. Create an account with MongoDB Atlas and create a new Database cluster.
//2. Create a database user underneath database access
//3. Whitelist your IP address for accessing the database
//4. While on the cluster overview click connect and you will see your connection string.
//5. Replace <username> and <password> with the database username and password you made. Remove <>.
//6. Done, you should be now able to connect to your database.

// =================================


// ======== EmailJS ================
// In client/src/components/feedback/Feedback.js 
//Replace the strings inside emailjs.sendForm('service_4bp0vbh', 'template_vwv381b', e.target, 'user_EY4qiL8ValKN3waEJEfET') with your own EmailJS ids

//Replace first field with your own service id, found underneath email service you create on EmailJS
//Replace second field with your own template id, found underneath template you create on EmailJS
//Replace fourth field with your own user id, found in integrations underneath API keys on EmailJS


//1. Create an account with Email JS.
//2. Add a new service, I recommend Gmail. Sign into a Gmail account to authorize EmailJS access to. It will send emails from this account. Create a new one if you want.
//3. Create a new email template. Use your own or as a default use {{{subject}}} for the subject line and put,
{{{name}}}

{{{email}}}

{{{message}}} 

// in the content area. Choose a desired email address to receive the emails.
//4. Done, you should be able to send emails using the feedback page.



 
