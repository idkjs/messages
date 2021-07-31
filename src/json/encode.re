include Messages.T;

type int = Stdlib.Int64.t;
type string = Stdlib.String.t;
type float = Stdlib.Float.t;
type bool = Stdlib.Bool.t;

type t('a) = Ezjsonm.value;

type app('a, 'b) = 'b => t('a);

let list = Ezjsonm.list;

let custom = (x => x, x => x);

let inject = x => x;

let str_atom = _ => Ezjsonm.string;

let int_atom = _ => Ezjsonm.int64;

let bool_atom = _ => Ezjsonm.bool;

let float_atom = _ => Ezjsonm.float;

type atom('a);
let atom: ('a, t('b)) => t(atom('a)) = (
  (_, v) => v: ('a, t('b)) => t(atom('a))
);

let pair = Ezjsonm.pair;

let triple = Ezjsonm.triple;

let either =
  fun
  | Left(t) => `A([Ezjsonm.int(0), t])
  | Right(t) => `A([Ezjsonm.int(1), t]);

let option = f =>
  fun
  | None => `Null
  | Some(t) => f(t);

let process =
  fun
  | `A(t) => `A(t)
  | `O(obj) => `O(obj)
  | other => `A([other]);
