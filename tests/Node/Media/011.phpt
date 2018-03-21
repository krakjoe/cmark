--TEST--
CommonMark\Node\Media write cached title
--FILE--
<?php
$link = new CommonMark\Node\Link;

$f = function($value) use($link) {
	return $link->title = $value;
};

var_dump($f("OK"), $f("KO"));
?>
--EXPECT--
string(2) "OK"
string(2) "KO"
