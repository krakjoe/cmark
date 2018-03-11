--TEST--
CommonMark\Node\Heading Level
--FILE--
<?php
$heading = new CommonMark\Node\Heading;
$heading->setHeadingLevel(3);

echo $heading->getHeadingLevel();
?>
--EXPECT--
3
