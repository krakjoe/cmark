--TEST--
CommonMark\Node\Media unset title cached
--FILE--
<?php
$link = new CommonMark\Node\Link("url", "OK");

$f = function() use($link) {
	unset($link->title);
};

var_dump($link->title);

$f();
$f();

var_dump($link->title);
?>
--EXPECT--
string(2) "OK"
NULL
