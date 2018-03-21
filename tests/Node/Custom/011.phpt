--TEST--
CommonMark\Node\Custom unset cached onEnter
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

$f = function() use($block) {
	var_dump($block->onEnter);
	unset($block->onEnter);
	var_dump($block->onEnter);
};

$block->onEnter = "OK";

$f();

$block->onEnter = "KO";

$f();
?>
--EXPECT--
string(2) "OK"
NULL
string(2) "KO"
NULL
