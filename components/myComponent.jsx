import React, { Component } from "react";
const fetch = require('node-fetch')
export default class Compo extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      title: "Ron"
    };
    this.getModels = this.getModels.bind(this);
  }
  getModels() {
    const apiUrl = 'http://localhost:9876/api/models/';
    fetch(apiUrl)
  .then(response => response.json())
  .then(data => this.setState({title: data.name}));
}
  render() {
    return (
      <div>
      <div> my name is: {this.state.title} </div>
      <button onClick={this.getModels}> Display My Name</button>
      </div>
    );
  }
}
