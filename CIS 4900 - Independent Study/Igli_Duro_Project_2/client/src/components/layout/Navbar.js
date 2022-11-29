import React, { Component } from "react";
import { Link } from "react-router-dom";
import './navbar.css';


class Navbar extends Component {
  render() {
    return (
      
      <div className="navbar-fixed">
       {/* <nav class="navbar navbar-expand-lg navbar-light bg-light">
          
          <div className="nav-wrapper white">
            <Link
              to="/"
              style={{
                fontFamily: "wolf2"
              }}
              className="col s5 brand-logo center black-text"
            >
              <i className="material-icons"></i>
              Project 2
            </Link>
            
            
          </div>
        </nav>
        */}
      </div>
              
    );
  }
}
export default Navbar;