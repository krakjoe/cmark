--TEST--
CommonMark\Node\Media read cached title
--FILE--
<?php
$link = new CommonMark\Node\Link;

$link->title = "OK";

$f = function() use($link) {
	return $link->title;
};

var_dump($f(), $f());
?>
--EXPECT--
string(2) "OK"
string(2) "OK"
