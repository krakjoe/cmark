--TEST--
CommonMark\Node\Media isset invalid
--FILE--
<?php
$link = new CommonMark\Node\Link;

var_dump(isset($link->something));
?>
--EXPECT--
bool(false)
