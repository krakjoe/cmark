--TEST--
CommonMark\Node\Media isset url
--FILE--
<?php
$link = new CommonMark\Node\Link;

var_dump(isset($link->url));

$link->url = "something";

var_dump(isset($link->url));
?>
--EXPECT--
bool(false)
bool(true)
