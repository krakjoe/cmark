--TEST--
CommonMark\Node\Custom cached write onEnter
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

$f = function($val) use($block) {
	return $block->onEnter = $val;
};

var_dump($f("OK"), $f("KO"));
?>
--EXPECT--
string(2) "OK"
string(2) "KO"
