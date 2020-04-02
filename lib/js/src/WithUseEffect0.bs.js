// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function WithUseEffect0(Props) {
  var match = React.useReducer((function (state, action) {
          return {
                  count: state.count + 1 | 0
                };
        }), {
        count: 0
      });
  var dispatch = match[1];
  React.useEffect((function () {
          var timerId = setInterval((function (param) {
                  return Curry._1(dispatch, /* Tick */0);
                }), 1000);
          return (function (param) {
                    clearInterval(timerId);
                    return /* () */0;
                  });
        }), ([]));
  return React.createElement("div", undefined, React.createElement("p", undefined, "Using useEffect0"), String(match[0].count));
}

var make = WithUseEffect0;

exports.make = make;
/* react Not a pure module */