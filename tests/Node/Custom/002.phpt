--TEST--
CommonMark\Node\Custom cached read onLeave
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

$block->onLeave = "OK";

$f = function() use($block) {
	return $block->onLeave;
};

var_dump($f(), $f());
?>
--EXPECT--
string(2) "OK"
string(2) "OK"
