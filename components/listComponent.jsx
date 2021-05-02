import React, { Component } from "react";
import Model from "./modelComponent";
import Compo from "./myComponent";


export default class List extends React.Component {

    state = {
        modelList : [ <Model/>, <Compo/>]
    };


    render() {
        return(
            <ul>
                {this.state.modelList}
            </ul>
        );
    }
}