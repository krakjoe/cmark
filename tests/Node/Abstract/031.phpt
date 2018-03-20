--TEST--
CommonMark\Node Traversable
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$doc->appendChild(new CommonMark\Node\Paragraph);
$para = $doc->firstChild;
$para->appendChild(new CommonMark\Node\Text("Hello"));
$doc->appendChild(new CommonMark\Node\BulletList);
$list = $doc->lastChild;
$list->appendChild(new CommonMark\Node\Item);

foreach ($doc as $ev => $node) {
	switch ($ev) {
		case CommonMark\Interfaces\IVisitor::Enter:
			printf("Enter: ");
		break;

		case CommonMark\Interfaces\IVisitor::Leave:
			printf("Leave: ");
		break;
	}
	printf("%s", get_class($node));

	if ($node instanceof CommonMark\Node\Text) {
		printf(": %s\n", $node->getLiteral());
	} else printf("\n");
}
?>
--EXPECT--
Enter: CommonMark\Node\Document
Enter: CommonMark\Node\Paragraph
Enter: CommonMark\Node\Text: Hello
Leave: CommonMark\Node\Paragraph
Enter: CommonMark\Node\BulletList
Enter: CommonMark\Node\Item
Leave: CommonMark\Node\Item
Leave: CommonMark\Node\BulletList
Leave: CommonMark\Node\Document
