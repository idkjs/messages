include Messages.T;

type int = Stdlib.Int.t;
type string = Stdlib.String.t;
type float = Stdlib.Float.t;
type bool = Stdlib.Bool.t;

type t('a) = Ojs.t;

type app('a, 'b) = 'b => t('a);

let list = Ojs.list_to_js;

let custom = (Obj.magic, Obj.magic);

let inject = x => x;

let str_atom = _ => Ojs.string_to_js;

let int_atom = _ => Ojs.int_to_js;

let bool_atom = _ => Ojs.bool_to_js;

let float_atom = _ => Ojs.float_to_js;

type atom('a);
let atom: ('a, t('b)) => t(atom('a)) = (
  (_, v) => v: ('a, t('b)) => t(atom('a))
);

let pair = (fa, fb, (a, b)) => {
  let arr = Ojs.array_make(2);
  Ojs.array_set(arr, 0, fa(a));
  Ojs.array_set(arr, 1, fb(b));
  arr;
};

let triple = (fa, fb, fc, (a, b, c)) => {
  let arr = Ojs.array_make(3);
  Ojs.array_set(arr, 0, fa(a));
  Ojs.array_set(arr, 1, fb(b));
  Ojs.array_set(arr, 2, fc(c));
  arr;
};

let either =
  fun
  | Left(t) => pair(Ojs.int_to_js, inject, (0, t))
  | Right(t) => pair(Ojs.int_to_js, inject, (1, t));

let option = Ojs.option_to_js;

let of_js_array:
  Js_of_ocaml.Js.t(Js_of_ocaml.Js.js_array('a)) => t(list('a)) = (
  Obj.magic: Js_of_ocaml.Js.t(Js_of_ocaml.Js.js_array('a)) => t(list('a))
);

let process: t('a) => Js_of_ocaml.Js.t(Js_of_ocaml.Js.js_string) = (
  t => Js_of_ocaml.Json.output(t):
    t('a) => Js_of_ocaml.Js.t(Js_of_ocaml.Js.js_string)
  /* Convert the result in a json object */
);
