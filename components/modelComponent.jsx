import React, { Component } from "react";


export default class Model extends React.Component {

    state = {
        id:1, 
        upload_time:"19:00:54",
        status : "pending"
    };


    render() {
        return(
            <ul>
            <li>{this.state.id}</li>
            <li>{this.state.upload_time}</li>
            <li>{this.state.status}</li>
            </ul>
        );
    }
}