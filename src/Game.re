let component = ReasonReact.statelessComponent "Game";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="game">
      <div className="game-board"> <Board /> </div>
      <div className="game-info"> <div /> <ol /> </div>
    </div>
};
