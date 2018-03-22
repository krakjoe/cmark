--TEST--
CommonMark\Node\Media isset url
--FILE--
<?php
$link = new CommonMark\Node\Link;

$f = function() use($link) {
	return isset($link->url);
};

var_dump($f());

$link->url = "something";

var_dump($f());
?>
--EXPECT--
bool(false)
bool(true)
