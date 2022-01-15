import "./TableData.css";

function TableData(props) {
  var unit = "";
  var dcolour = "black";
  if(props.name == "Available"){
    dcolour = "green";
  }
  else if(props.name == "Leaving Soon"){
    dcolour = "blue";
  }
  else if(props.name == "Occupied"){
    dcolour = "red";
  }
  if (props.name === "Zone") {
    if (props.data == 1){
      dcolour = "purple";
    }
    else if (props.data == 2){
      dcolour = "orange";
    }
    else if (props.data == 3){
      dcolour = "cyan";
    }
    else{
      dcolour = "grey";
    }
  }
  return (
    <div className="box">
      <label className="title">{props.name}</label>
      <div className="valuebox">
        <label className="val " style={{color: dcolour}}>{props.data}</label>
      </div>
    </div>
  );
}

export default TableData;
