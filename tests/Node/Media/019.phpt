--TEST--
CommonMark\Node\Media unset url
--FILE--
<?php
$link = new CommonMark\Node\Link("OK");

var_dump($link->url);

unset($link->url);

var_dump($link->url);
?>
--EXPECT--
string(2) "OK"
NULL
