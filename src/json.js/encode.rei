type t('a);

/** {2. Facilities function } */;

let process: t('a) => Js_of_ocaml.Js.t(Js_of_ocaml.Js.js_string);

/** {2. Encoder implementation } */;

include
  Messages.S with
    type app('a, 'b) = 'b => t('a) and
    type t('a) := t('a) and
    type string = Stdlib.String.t and
    type int = Stdlib.Int.t and
    type float = float and
    type bool = bool;

/** {2 Type explicitation}

    The functions here the same time as the Messages_common.S signature, but
    are explicited for better comprehension.

*/;

let list: ('a => t('b), list('a)) => t(list('b));

let str_atom: ('a, string) => t(str_atom('a));

let int_atom: ('a, int) => t(int_atom('a));

let bool_atom: ('a, bool) => t(bool_atom('a));

let float_atom: ('a, float) => t(float_atom('a));

let pair: ('a => t('a_), 'b => t('b_), ('a, 'b)) => t(('a_, 'b_));

let triple:
  ('a => t('a_), 'b => t('b_), 'c => t('c_), ('a, 'b, 'c)) =>
  t(('a_, 'b_, 'c_));

let either: either(t('a), t('b)) => t(either('a, 'b));

let option: ('b => t('a), option('b)) => t(option('a));

let of_js_array:
  Js_of_ocaml.Js.t(Js_of_ocaml.Js.js_array(t('a))) => t(list('a));

/** {2. Custom types} */;

let atom: ('a, t('b)) => t(atom('a));

let inject: t('a) => t('a);

let custom: (Js_of_ocaml.Js.t(_) => t('a), t(_) => Js_of_ocaml.Js.t('a));
