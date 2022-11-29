const mongoose = require("mongoose");
const Schema = mongoose.Schema;


// Create Schema
const UserSchema = new Schema ({
    name: {
        type: String,
        required: true
    },
    email: {
        type: String,
        required: true
    },
    school_name: {
        type: String,
        required: true
    },
    password: { 
        type: String,
        required: true
    },
    admin: { 
        type: Boolean,
        required: true,
        default: false
    },
    date: {
        type: Date,
        default: Date.now
    }
    
})

module.exports = User = mongoose.model ("users", UserSchema);
