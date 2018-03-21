--TEST--
CommonMark\Node\Media read cached url
--FILE--
<?php
$link = new CommonMark\Node\Link;

$link->url = "OK";

$f = function() use($link) {
	return $link->url;
};

var_dump($f(), $f());
?>
--EXPECT--
string(2) "OK"
string(2) "OK"
