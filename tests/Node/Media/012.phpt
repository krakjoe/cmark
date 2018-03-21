--TEST--
CommonMark\Node\Media write cached url
--FILE--
<?php
$link = new CommonMark\Node\Link;

$f = function($value) use($link) {
	return $link->url = $value;
};

var_dump($f("OK"), $f("KO"));
?>
--EXPECT--
string(2) "OK"
string(2) "KO"
