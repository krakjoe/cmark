--TEST--
CommonMark\Node\CodeBlock unset
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

$zero = 0;

try {
	unset($block->$zero);
} catch (RuntimeException $ex) {
	echo "OK\n";
}

$block->fence = "OK";

$f = function() use($block) {
	unset($block->fence);
};

$f();
$f();

var_dump(isset($block->fence));

try {
	unset($block->something);
} catch(RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
bool(false)
OK
