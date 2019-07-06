type timerId;
[@bs.val] external setTimeout: (unit => unit, int) => timerId = "setTimeout";
[@bs.val] external clearTimeout: timerId => unit = "clearTimeout";