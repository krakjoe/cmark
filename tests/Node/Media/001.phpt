--TEST--
CommonMark\Node\Media Title
--FILE--
<?php
$link = new CommonMark\Node\Media\Link;
$link->setTitle("OK");

echo $link->getTitle();
?>
--EXPECT--
OK
