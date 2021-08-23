import React, { Component } from 'react';
import "./App.css"
import autoBind from 'react-autobind';
import RadarChart from './component/radar';
import { Input } from 'reactstrap';
import { isMobile } from "react-device-detect"

function toTimestamp(strDate) {
  let datum = Date.parse(strDate);
  return datum;
}

function toDate(strDate) {
  let datum = strDate;
  let month = parseInt(datum.getMonth()) + 1
  if (month < 10) {
    month = "0" + month
  }
  datum = datum.getFullYear() + "-" + month + "-" + datum.getDate();
  console.log(datum)
  return datum;
}

class App extends Component {
  constructor(props) {
    super(props);
    autoBind(this);
    this.state = {
      data: [0, 0, 0]
    };
    this.unirest = require('unirest');
  }

  componentDidMount() {

  }

  componentWillUnmount() {

  }

  dateCallback(date) {
    console.log(date.target.value)
    const start = toTimestamp(date.target.value);
    const end = start + 86400000 * 2;
    console.log(start)
    console.log(end)
    this.unirest('GET', 'https://1yr5gnhrd1.execute-api.us-east-2.amazonaws.com/getDB')
      .headers({
        'first': start,
        'last': end
      })
      .end((res) => {
        if (res.error) throw new Error(res.error);
        let temp = JSON.parse(res.raw_body);
        let results = [0, 0, 0];
        for (let i = 0; i < temp.length; i++) {
          if (temp[i]["payload"]["res"] === "high") {
            results[0]++;
          } else if (temp[i]["payload"]["res"] === "medium") {
            results[1]++;
          }
          else if (temp[i]["payload"]["res"] === "low") {
            results[2]++;
          }
        }
        this.setState({
          data: results
        });
      }
      );
  }

  render() {
    return (
      <div>
        {
          isMobile ?
            <h1 className="textM" style={{ textAlign: "center" }}>
              Victor Exposure Analysis
              <p />
              <mark style={{ color: "yellow", WebkitTextStroke: "2px black" }}>AWS</mark><mark style={{ color: "blue" }}>BlueSpace</mark>[  ]
            </h1> :
            <h1 style={{ textAlign: "center" }}>
              Victor Exposure Analysis
              <p />
              <mark style={{ color: "yellow", WebkitTextStroke: "2px black" }}>AWS</mark><mark style={{ color: "blue" }}>BlueSpace</mark>[  ]
            </h1>
        }
        {
          isMobile ?
            <div className="centerM">
              <br />
              <Input style={{ fontSize: "1.8rem" }} onChange={this.dateCallback} type="date" min="2021-05-01" max={toDate(new Date(Date.now()))} />
              <br />
            </div>
            :
            <div className="center">
              <br />
              <Input style={{ fontSize: "1.3rem" }} onChange={this.dateCallback} type="date" min="2021-05-01" max={toDate(new Date(Date.now()))} />
              <br />
            </div>
        }
        <RadarChart data={this.state.data} />
      </div>
    );
  }
}

export default App;
