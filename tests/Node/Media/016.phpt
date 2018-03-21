--TEST--
CommonMark\Node\Media isset title
--FILE--
<?php
$link = new CommonMark\Node\Link;

var_dump(isset($link->title));

$link->title = "something";

var_dump(isset($link->title));
?>
--EXPECT--
bool(false)
bool(true)
