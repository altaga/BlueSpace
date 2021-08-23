import React from 'react';
import { Radar } from 'react-chartjs-2';
import { isMobile } from "react-device-detect"

function indexOfMax(arr) {
    if (arr.length === 0) {
        return -1;
    }

    var max = arr[0];
    var maxIndex = 0;

    for (var i = 1; i < arr.length; i++) {
        if (arr[i] > max) {
            maxIndex = i;
            max = arr[i];
        }
    }

    return maxIndex;
}

class RadarChart extends React.Component {
    render() {
        let data;
        if (indexOfMax(this.props.data) === 0) {
            data = {
                labels: ['High', 'Medium', 'Low'],
                datasets: [
                    {
                        label: '# Samples',
                        data: this.props.data,
                        backgroundColor: 'rgba(255, 0, 0, 0.2)',
                        borderColor: 'rgba(255, 0, 0, 1)',
                        borderWidth: 1,
                    },
                ],
            };
        }
        else if (indexOfMax(this.props.data) === 1) {
            data = {
                labels: ['High', 'Medium', 'Low'],
                datasets: [
                    {
                        label: '# Samples',
                        data: this.props.data,
                        backgroundColor: 'rgba(255, 255, 0, 0.2)',
                        borderColor: 'rgba(255, 255, 0, 1)',
                        borderWidth: 1,
                    },
                ],
            };
        }
        else if (indexOfMax(this.props.data) === 2) {
            data = {
                labels: ['High', 'Medium', 'Low'],
                datasets: [
                    {
                        label: '# Samples',
                        data: this.props.data,
                        backgroundColor: 'rgba(0, 255, 0, 0.2)',
                        borderColor: 'rgba(0, 255, 0, 1)',
                        borderWidth: 1,
                    },
                ],
            };
        }
        const options = {
            scale: {
                ticks: { beginAtZero: true },
            },
            scales: {
                r: {
                    angleLines: {
                        display: false
                    },
                    suggestedMin: Math.min.apply(Math, this.props.data) - 2,
                    pointLabels: {
                        font: {
                            size: 18,
                        },
                    },
                    ticks: {
                        font: {
                            size: 18,
                        },
                    }
                }
            },
            plugins: {
                legend: {
                    display: true,
                    labels: {
                        font: {
                            size: 18,
                        },
                    },
                }
            }
        };
        return (
            <>
                {
                    isMobile ?
                        <div className="center" style={{ width: "96vw" }}>
                            <Radar style={{ fontSize: "2rem" }} data={data} options={options} />
                        </div> :
                        <div className="center" style={{ width: "40vw" }}>
                            <Radar data={data} options={options} />
                        </div>
                }
            </>
        );
    }
}

export default RadarChart;
