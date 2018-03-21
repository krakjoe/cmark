--TEST--
CommonMark\Node\Custom cached write onLeave
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

$f = function($val) use($block) {
	return $block->onLeave = $val;
};

var_dump($f("OK"), $f("KO"));
?>
--EXPECT--
string(2) "OK"
string(2) "KO"
