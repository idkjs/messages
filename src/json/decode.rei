type t('a);

/** {2. Facilities function } */;

let process: Ezjsonm.t => t('a);

/** {2. Encoder implementation } */;

include
  Messages.S with
    type app('a, 'b) = t('a) => 'b and
    type t('a) := t('a) and
    type string = string and
    type int = int64 and
    type float = float and
    type bool = bool;

/** {2 Type explicitation}

    The functions here the same time as the Messages_common.S signature, but
    are explicited for better comprehension.

*/;

let list: (t('a) => 'b, t(list('a))) => list('b);

let str_atom: ('a, t(str_atom('a))) => string;

let int_atom: ('a, t(int_atom('a))) => int64;

let bool_atom: ('a, t(bool_atom('a))) => bool;

let float_atom: ('a, t(float_atom('a))) => float;

let pair: (t('a_) => 'a, t('b_) => 'b, t(('a_, 'b_))) => ('a, 'b);

let triple:
  (t('a_) => 'a, t('b_) => 'b, t('c_) => 'c, t(('a_, 'b_, 'c_))) =>
  ('a, 'b, 'c);

let either: t(either('a, 'b)) => either(t('a), t('b));

let option: (t('a) => 'b, t(option('a))) => option('b);

/** {2. Custom types} */;

let atom: ('a, t(atom('a))) => t('b);

let inject: t('a) => t('a);

let custom: (t('a) => Ezjsonm.value, Ezjsonm.value => t('a));
