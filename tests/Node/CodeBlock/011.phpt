--TEST--
CommonMark\Node\CodeBlock isset
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

$zero = 0;

var_dump(isset($block->$zero));

$f = function() use($block) {
	return isset($block->fence);
};

var_dump($f());

$block->fence = "OK";

var_dump($f());
?>
--EXPECT--
bool(false)
bool(false)
bool(true)
