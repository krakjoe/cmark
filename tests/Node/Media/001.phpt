--TEST--
CommonMark\Node\Media Title
--FILE--
<?php
$link = new CommonMark\Node\Link;
$link->title = "OK";

echo $link->title;
?>
--EXPECT--
OK
