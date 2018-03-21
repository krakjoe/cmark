--TEST--
CommonMark\Node\Custom cached read onEnter
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

$block->onEnter = "OK";

$f = function() use($block) {
	return $block->onEnter;
};

var_dump($f(), $f());
?>
--EXPECT--
string(2) "OK"
string(2) "OK"
