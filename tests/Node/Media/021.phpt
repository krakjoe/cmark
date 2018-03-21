--TEST--
CommonMark\Node\Media unset url cached
--FILE--
<?php
$link = new CommonMark\Node\Link("OK");

$f = function() use($link) {
	unset($link->url);
};

var_dump($link->url);

$f();
$f();

var_dump($link->url);
?>
--EXPECT--
string(2) "OK"
NULL
