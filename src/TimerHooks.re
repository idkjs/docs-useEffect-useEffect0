type state = {
  seconds: int,
  isTicking: bool,
};

let padNumber = numString =>
  if (numString |> int_of_string < 10) {
    "0" ++ numString;
  } else {
    numString;
  };

let formatTime = seconds => {
  let mins = seconds / 60;
  let minsString = mins |> string_of_int |> padNumber;
  let seconds = seconds mod 60;
  let secondsString = seconds |> string_of_int |> padNumber;
  minsString ++ ":" ++ secondsString;
};

module Button = {
  [@react.component]
  let make = (~label, ~onClick) => {
    <button onClick> {label |> ReasonReact.string} </button>;
  };
};

let updateTitle: string => unit = [%bs.raw
  {|
  function updateTitle(remaining) {
    document.title = "⏰ " + remaining + " ⏰";
  }|}
];
let initialState = {isTicking: false, seconds: 30};
[@react.component]
let make = () => {
  let (state, dispatch) = React.useState(() => initialState);

  let start = () => dispatch(_ => {...state, isTicking: true});
  let stop = () => dispatch(_ => {...state, isTicking: false});
  let reset = () => dispatch(_ => {...state, seconds: 30});
  let tick = () => {

    let newState = state.isTicking && state.seconds > 0
        ? {
          updateTitle(formatTime(state.seconds - 1));
          {...state, seconds: state.seconds - 1};
        }
        : state;


    dispatch(_ => newState);
  };

  React.useEffect(() => {
    let timerId = Js.Global.setInterval(() => tick(), 1000);
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div
    style={ReactDOMRe.Style.make(
      ~border="1px solid black",
      ~borderRadius="8px",
      ~maxWidth="180px",
      ~textAlign="center",
      (),
    )}>
    <p
      style={ReactDOMRe.Style.make(
        ~color="#444444",
        ~fontSize="42px",
        ~margin="16px 0",
        (),
      )}>
      {state.seconds |> formatTime |> ReasonReact.string}
    </p>
    {state.isTicking
       ? <Button label="STOP" onClick={_event => stop()} />
       : <>
           <Button label="START" onClick={_event => start()} />
           <Button label="RESET" onClick={_event => reset()} />
         </>}
  </div>;
};
