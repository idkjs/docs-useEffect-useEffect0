type action =
  | Tick;

type state = {count: int};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Tick => {count: state.count + 1}
        },
      {count: 0},
    );

  React.useEffect0(() => {
    let timerId = Js.Global.setInterval(() => dispatch(Tick), 1000);
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div> {ReasonReact.string(string_of_int(state.count))} </div>;
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useState(() => {count: 0});
  let tick = () => dispatch(_ => {count: state.count + 1});
  React.useEffect(() => {
    let timerId = Js.Global.setInterval(() => tick(), 1000);
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div> {ReasonReact.string(string_of_int(state.count))} </div>;
};
