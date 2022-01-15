import { useEffect, useState } from "react";
import "./App.css";
import TableData from "./Components/TableData.js";
import tabData from "./tableData.json";

const serverName = "http://192.168.31.241";

function App() {
  const [tableData, setTableData] = useState(tabData);

  const getData=()=>{
    fetch('./tableData.json'
    ,{
      headers : { 
        'Content-Type': 'application/json',
        'Accept': 'application/json'
       }
    }
    )
      .then(function(response){
        console.log(response)
        return response.json();
      })
      .then(function(myJson) {
        console.log(myJson);
        setTableData(myJson)
      });
  }
  useEffect(()=>{
    getData()
  },[])

  return (
    <div className="App">
      <div className="header">Table Occupancy System</div>
      {tableData.map(({Zone, Available, LeavingSoon, Occupied}) => (
          <div className="newRow">
          <TableData name="Zone" data={Zone} />
          <TableData name="Available" data={Available} />
          <TableData name="Leaving Soon" data={LeavingSoon} />
          <TableData name="Occupied" data={Occupied} />
          </div>
        ))}
    </div>
  );
}

export default App;
