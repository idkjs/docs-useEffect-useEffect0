type state = {count: int};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useState(() => {count: 0});
  let tick = () => dispatch(_ => {count: state.count + 1});
  React.useEffect(() => {
    let timerId = Js.Global.setInterval(() => tick(), 1000);
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div>
  <p>{ReasonReact.string("Using useEffect")}</p>
   {ReasonReact.string(string_of_int(state.count))} </div>;
};
