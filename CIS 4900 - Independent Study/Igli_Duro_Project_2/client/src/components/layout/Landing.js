import React, { Component } from "react";
import { Link } from "react-router-dom";

class Landing extends Component {
  render() {
    return (
      <div style={{ height: "50vh" }} className="container valign-wrapper">
        <div className="row">
          <div className="col center-align">
            <h3>
              <span style={{ fontFamily: "wolf2" }}> Login to continue or create an account.  </span>
            
            </h3>
            <p className="flow-text grey-text text-darken-1">
              
            </p>
            <br />
            <div className="col s6">
              <Link
                to="/login"
                style={{
                  width: "140px",
                  borderRadius: "3px",
                  letterSpacing: "1.5px"
                }}
                className="btn btn-large waves-effect waves-light hoverable blue accent-4"
              >
                Log In
              </Link>
            </div>
            <div className="col s6">
              <Link
                to="/register"
                style={{
                  width: "140px",
                  borderRadius: "3px",
                  letterSpacing: "1.5px"
                }}
                className="btn btn-large waves-effect waves-light hoverable blue accent-4"
              >
                Register
              </Link>
            </div>
          </div>
        </div>
      </div>
    );
  }
}
export default Landing;