--TEST--
CommonMark\Node\Media unset title
--FILE--
<?php
$link = new CommonMark\Node\Link("url", "OK");

var_dump($link->title);

unset($link->title);

var_dump($link->title);
?>
--EXPECT--
string(2) "OK"
NULL
