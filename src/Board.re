type state = {
  squares: list (option string),
  xIsNext: bool
};

type action =
  | Click int;

let stringOfOptionString value :string =>
  switch value {
  | None => ""
  | Some str => str
  };

let calculateWinner (squares: array (option string)) => {
  let lines = [
    (0, 1, 2),
    (3, 4, 5),
    (6, 7, 8),
    (0, 3, 6),
    (1, 4, 7),
    (2, 5, 8),
    (0, 4, 8),
    (2, 4, 6)
  ];
  List.fold_left
    (
      fun acc line => {
        let (a, b, c) = line;
        switch (squares.(a), squares.(b), squares.(c)) {
        | (Some a, Some b, Some c) when a !== "" && a === b && a === c => Some a
        | _ => acc
        }
      }
    )
    None
    lines
};

let component = ReasonReact.reducerComponent "Board";

let toggleSquare squares index turn =>
  List.mapi (fun i square => index === i ? turn : square) squares;

let make _children => {
  ...component,
  initialState: fun () => {squares: Array.to_list (Array.make 9 (Some "")), xIsNext: true},
  reducer: fun action state =>
    switch action {
    | Click (index: int) =>
      ReasonReact.Update {
        squares: toggleSquare state.squares index (Some (state.xIsNext ? "X" : "O")),
        xIsNext: not state.xIsNext
      }
    },
  render: fun {reduce, state} => {
    let renderSquare (index: int) =>
      <Square
        value=(stringOfOptionString (List.nth state.squares index))
        toggleSquare=(reduce (fun _event => Click index))
      />;
    let winner = calculateWinner (Array.of_list state.squares);
    let status =
      switch winner {
      | Some value => "Winner " ^ value
      | None => "Next player: " ^ (state.xIsNext ? "X" : "O")
      };
    <div>
      <div className="status"> (ReasonReact.stringToElement status) </div>
      <div className="board-row"> (renderSquare 0) (renderSquare 1) (renderSquare 2) </div>
      <div className="board-row"> (renderSquare 3) (renderSquare 4) (renderSquare 5) </div>
      <div className="board-row"> (renderSquare 6) (renderSquare 7) (renderSquare 8) </div>
    </div>
  }
};
