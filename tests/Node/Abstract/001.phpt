--TEST--
CommonMark\Node Append Child
--FILE--
<?php
$document = new CommonMark\Node\Document;
$paragraph = new CommonMark\Node\Paragraph;

$document->appendChild($paragraph);

echo "OK";
?>
--EXPECT--
OK
