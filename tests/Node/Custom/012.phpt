--TEST--
CommonMark\Node\Custom unset cached onLeave
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

$f = function() use($block) {
	var_dump($block->onLeave);
	unset($block->onLeave);
	var_dump($block->onLeave);
};

$block->onLeave = "OK";

$f();

$block->onLeave = "KO";

$f();
?>
--EXPECT--
string(2) "OK"
NULL
string(2) "KO"
NULL
