--TEST--
CommonMark\Node\Media isset invalid
--FILE--
<?php
$link = new CommonMark\Node\Link;

$zero = 0;

var_dump(isset($link->$zero));
?>
--EXPECT--
bool(false)
