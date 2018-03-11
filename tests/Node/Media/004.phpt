--TEST--
CommonMark\Node\Media URL
--FILE--
<?php
$link = new CommonMark\Node\Media\Link;
$link->setURL("OK");

echo $link->getURL();
?>
--EXPECT--
OK
