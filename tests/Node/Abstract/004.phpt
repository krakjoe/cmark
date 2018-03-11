--TEST--
CommonMark\Node Prepend Child
--FILE--
<?php
$document = new CommonMark\Node\Document;
$paragraph = new CommonMark\Node\Paragraph;

$document->prependChild($paragraph);

echo "OK";
?>
--EXPECT--
OK
