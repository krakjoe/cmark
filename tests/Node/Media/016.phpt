--TEST--
CommonMark\Node\Media isset title
--FILE--
<?php
$link = new CommonMark\Node\Link;

$f = function() use($link) {
	return isset($link->title);
};

var_dump($f());

$link->title = "something";

var_dump($f());
?>
--EXPECT--
bool(false)
bool(true)
