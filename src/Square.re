let component = ReasonReact.statelessComponent "Square";

let make ::value ::toggleSquare _children => {
  ...component,
  render: fun _self =>
    <button className="square" onClick=toggleSquare> (ReasonReact.stringToElement value) </button>
};
