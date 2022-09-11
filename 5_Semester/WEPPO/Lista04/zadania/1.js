/*
WEPPO - Lista 4, zad 1
Artur Jankowski, indeks: 317928
*/

function Tree(val, left, right) {
  this.left = left;
  this.right = right;
  this.val = val;
}
Tree.prototype[Symbol.iterator] = function*(){  //The Symbol.iterator specifies the default iterator for an object. Used by for...of.
  let queue = [this]; // start with root node
  
  while (queue.length != 0) {
    let node = queue.shift(); // return top of queue and delete it (basically pop() on a queue)
  
    if (typeof node.right != 'undefined') {
      queue.push(node.right);
    }

    if (typeof node.left != 'undefined') {
      queue.push(node.left);
    }

    yield node.val;
  }
}
  
var root = new Tree( 1,
  new Tree( 2, new Tree( 3 ) ), new Tree( 4 ));

/*
     1 
  2     4
3   
*/
for ( var e of root ) {
  console.log( e );
}

/*
let tab = [1, 2, 3, 4];
let top = 0;
console.log(tab.splice(0, 1, top));
console.log(tab);
*/