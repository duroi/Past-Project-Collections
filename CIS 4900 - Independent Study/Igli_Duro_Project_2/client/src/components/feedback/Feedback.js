import emailjs from "emailjs-com";
import React from 'react';

export default function Feedback() {

    function sendEmail(e) {
        e.preventDefault();

    //Replace first field with your own service id, found underneath email service you create on EmailJS
    //Replace second field with your own template id, found underneath template you create on EmailJS
    //Replace fourth field with your own user id, found in integrations underneath API keys on EmailJS

    emailjs.sendForm('service_4bp0vbh', 'template_vwv381b', e.target, 'user_EY4qiL8ValKN3waEJEfET')
        .then((result) => {
            console.log(result.text);
        }, (error) => {
            console.log(error.text);
        });
        e.target.reset()
    }

    return(
        <div>
        <div className="row">
          <div className="col s12 center-align">
            <h3>
              <span style={{ fontFamily: "wolf2" }}> Contact Us </span>
              </h3>
              </div>
              </div>
            <div className="container">
            <form onSubmit={sendEmail}>
                    <div className="row pt-5 mx-auto">

                        {/* NAME FIELD */}
                        <div className="col-8 form-group mx-auto">
                            <input type="text" className="form-control" placeholder="Name" name="name"/>
                        </div>
                        
                        {/* EMAIL FIELD */}
                        <div className="col-8 form-group pt-2 mx-auto">
                            <input type="email" className="form-control" placeholder="Email Address" name="email"/>
                        </div>
                        
                        {/* SUBJECT FIELD */}
                        <div className="col-8 form-group pt-2 mx-auto">
                            <input type="text" className="form-control" placeholder="Subject" name="subject"/>
                        </div>
                        
                        
                        {/* MESSAGE FIELD */}
                        <div className="col-8 form-group pt-2 mx-auto">
                            <textarea className="form-control" id="" cols="30" rows="8" placeholder="Your message" name="message"></textarea>
                        </div>
                        
                        
                        {/* SEND MESSAGE */}
                        <div className="col-8 pt-3 mx-auto">
                            <input type="submit" className="btn btn-large waves-effect waves-light hoverable blue accent-4" value="Send Message"></input>
                        </div>
                    </div>
                </form>
            </div>
        </div>
    )
}